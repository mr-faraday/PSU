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

INSERT INTO document_subject (document_subject_name)
VALUES
    ('Организационно-распорядительной документация'),
    ('Плановой документация'),
    ('Первичная учѐтная документация'),
    ('Отчётно-статистическая документация'),
    ('Документация по труду'),
    ('Бухгалтерской документация'),
    ('Финансовая и расчётно-денежная документация'),
    ('Статистической и ведомственной отчётности');

INSERT INTO department (department_id, phone_number)
VALUES
    (1, '80214667788'),
    (2, '80214468413'),
    (3, '80214145112'),
    (4, '80214979846'),
    (5, '80214187436'),
    (6, '80214168796'),
    (7, '80214468981');

INSERT INTO subscriber (first_name, last_name, middle_name, subscriber_number, department_id)
VALUES
    ('Tabor', 'Clemmens', 'Siana', '2044160315', 1),
    ('Mindy', 'Courson', 'Renee', '3542421065', 2),
    ('Kerri', 'Alwin', 'Stevie', '0289830664', 2),
    ('Shaughn', 'Cushworth', 'Erskine', '2875461559', 3),
    ('Wenona', 'Haistwell', 'Sandy', '3283390940', 1),
    ('Gizela', 'Djordjevic', 'Fergus', '1577700368', 1),
    ('Victor', 'Kasting', 'Siegfried', '6999156697', 2),
    ('Ignacio', 'Noulton', 'Elka', '1433321815', 3),
    ('Jana', 'Whistlecroft', 'Steven', '4344639693', 2),
    ('Callida', 'MacConnel', 'Lianna', '8087905393', 5),
    ('Arlen', 'Natte', 'Reinaldos', '6383641786', 4),
    ('Milli', 'Sillars', 'Cassie', '0103909737', 1),
    ('Gayel', 'Caunce', 'Ninette', '3624038125', 3),
    ('Torrey', 'Rowsel', 'Hasheem', '8977858194', 1),
    ('Cherise', 'Laws', 'Flin', '1746134399', 4),
    ('Cahra', 'Lode', 'Donielle', '4539747991', 3),
    ('Madelin', 'Kmieciak', 'Sharlene', '9985099915', 2),
    ('Jody', 'Bowering', 'Giraldo', '3933752140', 7),
    ('Gran', 'Devereux', 'Nil', '0922049688', 1),
    ('Mame', 'Marden', 'Maiga', '4481957808', 5),
    ('Malina', 'Sturton', 'Kathie', '5524229478', 3),
    ('Broderic', 'Capelin', 'Taddeusz', '0559617097', 4),
    ('Blithe', 'Blanning', 'Celka', '1578612969', 1),
    ('Alfons', 'Nanuccioi', 'Cassy', '9351273482', 3),
    ('Aeriel', 'Murty', 'Farly', '6991941530', 4),
    ('Zorina', 'Bordone', 'Josh', '6320216557', 5),
    ('Hobard', 'Cantwell', 'Bill', '2478615835', 3),
    ('Ynes', 'McRinn', 'Romy', '0058833706', 4),
    ('Vida', 'Edgeworth', 'Patricio', '8515291509', 2),
    ('Delmor', 'Grzegorecki', 'Linn', '5776552206', 7),
    ('Pail', 'Cavan', 'Marius', '2031431927', 4),
    ('Keith', 'Truter', 'Alexio', '1714791998', 6),
    ('Perri', 'Goodban', 'Ignaz', '5364700585', 1),
    ('Sloan', 'Clausewitz', 'Correna', '2813868418', 7),
    ('Pacorro', 'Shannon', 'Maddy', '4894117398', 5),
    ('Dulcine', 'Strood', 'Rusty', '3602798127', 3),
    ('Sibylle', 'Chern', 'Emmye', '8565211940', 4),
    ('Carmina', 'Vint', 'Armand', '2204124087', 6),
    ('Briney', 'Micallef', 'Cosette', '7265729757', 6),
    ('Terrell', 'Lumly', 'Giorgia', '9405841793', 7);


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
INSERT INTO rack
select id, concat(id + 100000000)
FROM GENERATE_SERIES(1, current_setting('my.number_of_racks')::int) as id;

-- Filling of shelfs
INSERT INTO shelf
select
    id,
    concat(id + 200000000),
    floor(random() * current_setting('my.number_of_racks')::int) + 1
FROM GENERATE_SERIES(1, current_setting('my.number_of_shelfs')::int) as id;

-- Filling of cells
INSERT INTO cell
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

            SELECT COUNT(*) INTO is_occupied FROM document
            WHERE cell_id = cell;

            IF is_occupied > 0
			THEN
                cell := null;
            END IF;

        END LOOP;

        INSERT INTO document (document_id, document_name, inventory_number, arrived_at, cell_id, document_subject_id)
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

INSERT INTO document_copy
select
    id,
    concat('COPY_', id + 1000),
    concat(id + 500000000),
    floor(random() * current_setting('my.number_of_documents')::int) + 1
FROM GENERATE_SERIES(1, current_setting('my.number_of_copies')::int) as id;
