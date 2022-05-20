-- warehause

CREATE TABLE IF NOT EXISTS racks (
    id SERIAL,
    rack_number varchar(50) NOT NULL CHECK (length(rack_number) > 0) UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS shelfs (
    id SERIAL,
    shelf_number varchar(50) NOT NULL CHECK (length(shelf_number) > 0) UNIQUE,
    rack_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_rack_id
        FOREIGN KEY (rack_id)
	    REFERENCES racks(id)
);

CREATE TABLE IF NOT EXISTS cells (
    id SERIAL,
    cell_number varchar(50) NOT NULL CHECK (length(cell_number) > 0) UNIQUE,
    shelf_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_shelf_id
        FOREIGN KEY (shelf_id)
	    REFERENCES shelfs(id)
);

-- documents

CREATE TABLE IF NOT EXISTS document_subjects (
    id SERIAL,
    name varchar(255) NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS documents (
    id SERIAL,
    name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    arrived_at timestamptz NOT NULL,
    cell_id int NOT NULL UNIQUE,
    subject_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_cell_id
        FOREIGN KEY (cell_id)
        REFERENCES cells(id),
    CONSTRAINT fk_subject_id
        FOREIGN KEY (subject_id)
        REFERENCES document_subjects(id)
);

CREATE TABLE IF NOT EXISTS document_copies (
    id SERIAL,
    name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    document_id int NOT NULL,

    PRIMARY KEY(id),
    CONSTRAINT fk_document_id
        FOREIGN KEY (document_id)
        REFERENCES documents(id)
);

-- subscribers

CREATE TABLE IF NOT EXISTS departments (
    id SERIAL,
    phone_number varchar(255),

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS subscribers (
    id SERIAL,
    first_name varchar(255) NOT NULL CHECK (length(first_name) > 0),
    last_name varchar(255) NOT NULL CHECK (length(last_name) > 0),
    middle_name varchar(255) CHECK (length(middle_name) > 0),
    subscriber_number varchar(50) NOT NULL CHECK (length(subscriber_number) > 0) UNIQUE,
    department_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_department_id
        FOREIGN KEY (department_id)
        REFERENCES departments(id)
);

-- issues

CREATE TABLE IF NOT EXISTS document_issues (
    id SERIAL,
    issued_at timestamptz NOT NULL,
    returned_at timestamptz,
    subscriber_id int NOT NULL,
    document_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_subscriber_id
        FOREIGN KEY (subscriber_id)
        REFERENCES subscribers(id),
    CONSTRAINT fk_document_id
        FOREIGN KEY (document_id)
        REFERENCES documents(id),
    CHECK (returned_at > issued_at OR returned_at is null)
);

-- EMPLOYEES

CREATE TABLE IF NOT EXISTS employee_roles (
    id SERIAL,
    name varchar(255) NOT NULL CHECK (length(name) > 0) UNIQUE,

    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS employees (
    id SERIAL,
    name varchar(255) NOT NULL CHECK (length(name) > 0) UNIQUE,
    password varchar(255) NOT NULL CHECK (length(password) > 0),
    role_id int NOT NULL,

    PRIMARY KEY (id),
    CONSTRAINT fk_role_id
        FOREIGN KEY (role_id)
        REFERENCES employee_roles(id)
);
