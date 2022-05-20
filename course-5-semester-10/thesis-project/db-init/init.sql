-- warehause

CREATE TABLE IF NOT EXISTS racks (
    rack_id int GENERATED BY DEFAULT AS IDENTITY,
    rack_number varchar(50) NOT NULL CHECK (length(rack_number) > 0) UNIQUE,

    PRIMARY KEY (rack_id)
);

CREATE TABLE IF NOT EXISTS shelfs (
    shelf_id int GENERATED BY DEFAULT AS IDENTITY,
    shelf_number varchar(50) NOT NULL CHECK (length(shelf_number) > 0) UNIQUE,
    rack_id int NOT NULL,

    PRIMARY KEY (shelf_id),
    CONSTRAINT fk_rack_id
        FOREIGN KEY (rack_id)
	    REFERENCES racks(rack_id)
);

CREATE TABLE IF NOT EXISTS cells (
    cell_id int GENERATED BY DEFAULT AS IDENTITY,
    cell_number varchar(50) NOT NULL CHECK (length(cell_number) > 0) UNIQUE,
    shelf_id int NOT NULL,

    PRIMARY KEY (cell_id),
    CONSTRAINT fk_shelf_id
        FOREIGN KEY (shelf_id)
	    REFERENCES shelfs(shelf_id)
);

-- documents

CREATE TABLE IF NOT EXISTS document_subjects (
    document_subject_id int GENERATED BY DEFAULT AS IDENTITY,
    document_subject_name varchar(255) NOT NULL,

    PRIMARY KEY (document_subject_id)
);

CREATE TABLE IF NOT EXISTS documents (
    document_id int GENERATED BY DEFAULT AS IDENTITY,
    document_name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    arrived_at timestamptz NOT NULL,
    cell_id int NOT NULL UNIQUE,
    document_subject_id int NOT NULL,

    PRIMARY KEY (document_id),
    CONSTRAINT fk_cell_id
        FOREIGN KEY (cell_id)
        REFERENCES cells(cell_id),
    CONSTRAINT fk_document_subject_id
        FOREIGN KEY (document_subject_id)
        REFERENCES document_subjects(document_subject_id)
);

CREATE TABLE IF NOT EXISTS document_copies (
    copy_id int GENERATED BY DEFAULT AS IDENTITY,
    copy_name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    document_id int NOT NULL,

    PRIMARY KEY(copy_id),
    CONSTRAINT fk_document_id
        FOREIGN KEY (document_id)
        REFERENCES documents(document_id)
);

-- subscribers

CREATE TABLE IF NOT EXISTS departments (
    department_id int GENERATED BY DEFAULT AS IDENTITY,
    phone_number varchar(255),

    PRIMARY KEY (department_id)
);

CREATE TABLE IF NOT EXISTS subscribers (
    subscriber_id int GENERATED BY DEFAULT AS IDENTITY,
    first_name varchar(255) NOT NULL CHECK (length(first_name) > 0),
    last_name varchar(255) NOT NULL CHECK (length(last_name) > 0),
    middle_name varchar(255) CHECK (length(middle_name) > 0),
    subscriber_number varchar(50) NOT NULL CHECK (length(subscriber_number) > 0) UNIQUE,
    department_id int NOT NULL,

    PRIMARY KEY (subscriber_id),
    CONSTRAINT fk_department_id
        FOREIGN KEY (department_id)
        REFERENCES departments(department_id)
);

-- issues

CREATE TABLE IF NOT EXISTS document_issues (
    issue_id int GENERATED BY DEFAULT AS IDENTITY,
    issued_at timestamptz NOT NULL,
    returned_at timestamptz,
    subscriber_id int NOT NULL,
    document_id int NOT NULL,

    PRIMARY KEY (issue_id),
    CONSTRAINT fk_subscriber_id
        FOREIGN KEY (subscriber_id)
        REFERENCES subscribers(subscriber_id),
    CONSTRAINT fk_document_id
        FOREIGN KEY (document_id)
        REFERENCES documents(document_id),
    CHECK (returned_at > issued_at OR returned_at is null)
);

-- USERS

CREATE TABLE IF NOT EXISTS user_roles (
    user_role_id int GENERATED BY DEFAULT AS IDENTITY,
    user_role_name varchar(255) NOT NULL CHECK (length(user_role_name) > 0) UNIQUE,

    PRIMARY KEY (user_role_id)
);

CREATE TABLE IF NOT EXISTS users (
    user_id int GENERATED BY DEFAULT AS IDENTITY,
    user_name varchar(255) NOT NULL CHECK (length(user_name) > 0) UNIQUE,
    user_password varchar(255) NOT NULL CHECK (length(user_password) > 0),
    user_role_id int NOT NULL,

    PRIMARY KEY (user_id),
    CONSTRAINT fk_user_role_id
        FOREIGN KEY (user_role_id)
        REFERENCES user_roles(user_role_id)
);
