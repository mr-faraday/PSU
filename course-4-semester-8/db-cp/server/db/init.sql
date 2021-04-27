-- warehause

CREATE TABLE IF NOT EXISTS rack (
    rack_id GENERATED ALWAYS AS IDENTITY,
    rack_number int NOT NULL,

    PRIMARY KEY (rack_id)
);

CREATE TABLE IF NOT EXISTS shelf (
    shelf_id GENERATED ALWAYS AS IDENTITY,
    shelf_number int NOT NULL,
    rack_id int NOT NULL,

    PRIMARY KEY (shelf_id),
    CONSTRAINT fk_rack
        FOREIGN KEY (rack_id)
	    REFERENCES rack(rack_id)
);

CREATE TABLE IF NOT EXISTS cell (
    cell_id GENERATED ALWAYS AS IDENTITY,
    cell_number int NOT NULL,
    shelf_id int NOT NULL,

    PRIMARY KEY (cell_id),
    CONSTRAINT fk_shelf
        FOREIGN KEY (shelf_id)
	    REFERENCES shelf(shelf_id)
);

-- documents

CREATE TABLE IF NOT EXISTS document_subject (
    document_subject_id GENERATED ALWAYS AS IDENTITY,
    document_subject_name varchar(255) NOT NULL

    PRIMARY KEY (document_subject_id)
);

CREATE TABLE IF NOT EXISTS document (
    document_id GENERATED ALWAYS AS IDENTITY,
    document_name varchar(255) NOT NULL,
    inventory_number int NOT NULL,
    arrival_date timestamp NOT NULL,
    cell_id int NOT NULL,
    document_subject_id int NOT NULL,

    PRIMARY KEY (document_id),
    CONSTRAINT fk_cell
        FOREIGN KEY (cell_id)
        REFERENCES cell(cell_id),
    CONSTRAINT fk_document_subject
        FOREIGN KEY (document_subject_id)
        REFERENCES document_subject(document_subject_id)
);

-- subscribers

CREATE TABLE IF NOT EXISTS department (
    department_id GENERATED ALWAYS AS IDENTITY,
    phone_number varchar(255) NOT NULL

    PRIMARY KEY (department_id)
);

CREATE TABLE IF NOT EXISTS subscriber (
    subscriber_id GENERATED ALWAYS AS IDENTITY,
    first_name varchar(255) NOT NULL,
    last_name varchar(255) NOT NULL,
    middle_name varchar(255) NOT NULL,
    subscriber_number int NOT NULL,
    department_id int NOT NULL,

    PRIMARY KEY (subscriber_id),
    CONSTRAINT fk_department
        FOREIGN KEY (department_id)
        REFERENCES department(department_id)
);

-- extradition

CREATE TABLE IF NOT EXISTS extradition (
    extradition_id GENERATED ALWAYS AS IDENTITY,
    extradition_date timestamp NOT NULL,
    return_date timestamp,
    subscriber_id int NOT NULL,
    document_id int NOT NULL,

    PRIMARY KEY (extradition_id),
    CONSTRAINT fk_subscriber
        FOREIGN KEY (subscriber_id)
        REFERENCES subscriber(subscriber_id)б
    CONSTRAINT fk_document
        FOREIGN KEY (document_id)
        REFERENCES document(document_id)
);
