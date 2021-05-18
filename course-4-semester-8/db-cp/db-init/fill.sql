CREATE FUNCTION random_timestamp() returns timestamp
	language plpgsql
	AS $$
	begin
	    return timestamp '2001-01-10 20:00:00' + random() * timestamp '2022-01-20 20:00:00';
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
set session my.number_of_extraditios = '21589';

set session my.start_date = '2019-01-01 00:00:00';
set session my.end_date = '2020-02-01 00:00:00';

-- load the pgcrypto extension to gen_random_uuid ()
CREATE EXTENSION pgcrypto;

-- Filling of racks
INSERT INTO rack
select id, concat(num + 100000000)
FROM GENERATE_SERIES(1, current_setting('my.number_of_racks')::int) as id;

-- Filling of shelfs
INSERT INTO shelf
select
    id
    concat(id + 200000000),
    floor(random() * (current_setting('my.number_of_racks')::int + 1))::int
FROM GENERATE_SERIES(1, current_setting('my.number_of_shelfs')::int) as id;

-- Filling of cells
INSERT INTO cell
select
    id
    concat(id + 300000000),
    floor(random() * (current_setting('my.number_of_shelfs')::int + 1))::int
FROM GENERATE_SERIES(1, current_setting('my.number_of_cells')::int) as id;

INSERT INTO document
select
    id
    concat('DOC_', id + 1000),
    concat(id + 400000000),
    random_timestamp(),
    floor(random() * (current_setting('my.number_of_cells')::int + 1))::int,
    floor(random() * (current_setting('my.number_of_subjects')::int + 1))::int
FROM GENERATE_SERIES(1, current_setting('my.number_of_documents')::int) as id;

INSERT INTO document_copy
select
    id
    concat('COPY_', id + 1000),
    concat(id + 500000000),
    floor(random() * (current_setting('my.number_of_documents')::int + 1))::int
FROM GENERATE_SERIES(1, current_setting('my.number_of_documents')::int) as id;

-- extraditions

CREATE PROCEDURE create_extradition()
BEGIN
    DECLARE extradition_length, i INT;
    DECLARE extradition_date, return_date, returned_at timestamp;
    DECLARE document_ids_currently_in_use, available_document_ids int;
    -- DECLARE some_cur CURSOR FOR
        -- SELECT `day`, `menu_id` FROM menus_days_mealslists GROUP BY day, menu_id ORDER BY menu_id;
        -- some cursor
    -- DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    extradition_length := current_setting('my.number_of_extraditios')::int;
    i := 0;

    -- OPEN some_cur;

    extraditions_loop LOOP
        IF i > extradition_length THEN
            LEAVE extraditions_loop;
        END IF;

        extradition_date := random_timestamp()
        return_date := extradition_date + random() * 3600 * 24 * 365

        IF now() > return_date THEN
            returned_at := return_date
        ELSE
            returned_at := NULL
        END IF;


        -- FETCH some_cur INTO var1, var2;

        -- Get documents currently in use
        SELECT document_id INTO document_ids_currently_in_use FROM extradition AS item
        WHERE
            returned_at > item.extradition_date AND
            (returned_at < item.return_date OR returned_at = null)
        GROUP BY document_id;

        SELECT document_id INTO available_document_ids FROM document AS doc
        WHERE
            extradition_date > doc.arrival_date AND
            (SELECT COUNT(*) FROM document_ids_currently_in_use WHERE doc.documet_id = document_id) = 0;

        IF (SELECT COUNT(*) FROM available_document_ids) = 0
            RAISE EXCEPTION 'No available in available_document_ids, please restart';
        END IF;

        -- get documet_id
        

        INSERT INTO extradition (extradition_date, return_date, subscriber_id, document_id)
            VALUES (/* data */);
        
        i := i + 1;
    END LOOP extraditions_loop;

    -- CLOSE some_cur;
END

CALL create_extradition();
DROP PROCEDURE IF EXISTS create_extradition;



-- 	language plpgsql
-- 	AS $$
--     declare
--         document_id int;
--         extradition_date timestamp;
-- 	begin
-- 	    return timestamp '2001-01-10 20:00:00' + random() * timestamp '2020-01-20 20:00:00';
-- 	end;
-- 	$$;

-- INSERT INTO extradition
-- select
--     id
--     random_timestamp(), -- extradition_date
--     random_timestamp(), -- return_date
--     floor(random() * (current_setting('my.number_of_subscribers')::int + 1))::int,
--     floor(random() * (current_setting('my.number_of_documents')::int + 1))::int,

-- FROM GENERATE_SERIES(1, current_setting('my.number_of_extraditios')::int) as id;

-- DROP FUNCTION random_timestamp, create_extradition;
