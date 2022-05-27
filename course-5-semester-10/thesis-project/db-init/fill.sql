CREATE OR REPLACE FUNCTION random_timestamp(since timestamptz DEFAULT timestamptz '2001-01-10T20:00:00Z') returns timestamptz
	language plpgsql
	AS $$
	begin
	    return TO_TIMESTAMP(
			EXTRACT(EPOCH FROM since) +
			floor(random() * (
				EXTRACT(EPOCH FROM timestamptz '2021-01-10T20:00:00Z') -
				EXTRACT(EPOCH FROM since)
            ))
		);
	end;
	$$;

INSERT INTO subscribers (first_name, last_name, middle_name)
VALUES
    ('Tabor', 'Clemmens', 'Siana'),
    ('Mindy', 'Courson', 'Renee'),
    ('Kerri', 'Alwin', 'Stevie'),
    ('Shaughn', 'Cushworth', 'Erskine'),
    ('Wenona', 'Haistwell', 'Sandy'),
    ('Gizela', 'Djordjevic', 'Fergus'),
    ('Victor', 'Kasting', 'Siegfried'),
    ('Ignacio', 'Noulton', 'Elka'),
    ('Jana', 'Whistlecroft', 'Steven'),
    ('Callida', 'MacConnel', 'Lianna'),
    ('Arlen', 'Natte', 'Reinaldos'),
    ('Milli', 'Sillars', 'Cassie'),
    ('Gayel', 'Caunce', 'Ninette'),
    ('Torrey', 'Rowsel', 'Hasheem'),
    ('Cherise', 'Laws', 'Flin'),
    ('Cahra', 'Lode', 'Donielle'),
    ('Madelin', 'Kmieciak', 'Sharlene'),
    ('Jody', 'Bowering', 'Giraldo'),
    ('Gran', 'Devereux', 'Nil'),
    ('Mame', 'Marden', 'Maiga');


-- Set params
set session my.number_of_racks = '30';
set session my.number_of_shelfs = '200';
set session my.number_of_cells = '1200';
set session my.number_of_documents = '700';
set session my.number_of_subjects = '8';
set session my.number_of_copies = '7550';
set session my.number_of_subscribers = '40';

set session my.start_date = '2019-01-01 00:00:00';
set session my.end_date = '2020-02-01 00:00:00';

-- load the pgcrypto extension to gen_random_uuid ()
CREATE EXTENSION pgcrypto;

-- Filling of racks
INSERT INTO racks
select id, concat(id + 100000000)
FROM GENERATE_SERIES(1, current_setting('my.number_of_racks')::int) as id;

-- Filling of shelfs
INSERT INTO shelfs
select
    id,
    concat(id + 200000000),
    floor(random() * current_setting('my.number_of_racks')::int) + 1
FROM GENERATE_SERIES(1, current_setting('my.number_of_shelfs')::int) as id;

-- Filling of cells
INSERT INTO cells
select
    id,
    concat(id + 300000000),
    floor(random() * current_setting('my.number_of_shelfs')::int) + 1
FROM GENERATE_SERIES(1, current_setting('my.number_of_cells')::int) as id;

-- fill documents
CREATE OR REPLACE PROCEDURE fill_documents()
LANGUAGE plpgsql
AS $$
DECLARE
    documents_length INT := current_setting('my.number_of_documents')::int;
    i INT := 1;
    cell INT := null;
    is_occupied INT := 0;
BEGIN
    <<doc_loop>> LOOP
        IF i > documents_length THEN
            EXIT doc_loop;
        END IF;

        WHILE cell IS NULL LOOP
            cell := floor(random() * current_setting('my.number_of_cells')::int) + 1;

            SELECT COUNT(*) INTO is_occupied FROM documents
            WHERE cell_id = cell;

            IF is_occupied > 0
			THEN
                cell := null;
            END IF;

        END LOOP;

        INSERT INTO documents (id, name, inventory_number, arrived_at, cell_id, subject_id)
        VALUES (
            i,
            concat('DOC_', i + 1000),
            concat(i + 400000000),
            random_timestamp(),
            cell,
            floor(random() * current_setting('my.number_of_subjects')::int) + 1
        );

        cell := null;
        i := i + 1;
    END LOOP doc_loop;
END
$$;

CALL fill_documents();
DROP PROCEDURE IF EXISTS fill_documents;

INSERT INTO document_copies
select
    id,
    concat('COPY_', id + 1000),
    concat(id + 500000000),
    floor(random() * current_setting('my.number_of_documents')::int) + 1
FROM GENERATE_SERIES(1, current_setting('my.number_of_copies')::int) as id;

INSERT INTO employee_roles (id, name) VALUES (1, 'admin');
INSERT INTO employee_roles (id, name) VALUES (2, 'user');
