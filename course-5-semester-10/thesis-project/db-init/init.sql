-- warehause

CREATE TABLE IF NOT EXISTS racks (
    id SERIAL PRIMARY KEY,
    rack_number varchar(50) NOT NULL CHECK (length(rack_number) > 0) UNIQUE
);

CREATE TABLE IF NOT EXISTS shelfs (
    id SERIAL PRIMARY KEY,
    shelf_number varchar(50) NOT NULL CHECK (length(shelf_number) > 0) UNIQUE,
    rack_id int NOT NULL REFERENCES racks(id)
);

CREATE TABLE IF NOT EXISTS cells (
    id SERIAL PRIMARY KEY,
    cell_number varchar(50) NOT NULL CHECK (length(cell_number) > 0) UNIQUE,
    shelf_id int NOT NULL REFERENCES shelfs(id)
);

-- documents

CREATE TABLE IF NOT EXISTS document_subjects (
    id SERIAL PRIMARY KEY,
    name varchar(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS documents (
    id SERIAL PRIMARY KEY,
    name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    arrived_at timestamptz NOT NULL,
    cell_id int NOT NULL UNIQUE REFERENCES cells(id),
    subject_id int NOT NULL REFERENCES document_subjects(id)        
);

CREATE TABLE IF NOT EXISTS document_copies (
    id SERIAL PRIMARY KEY,
    name varchar(255) NOT NULL,
    inventory_number varchar(50) NOT NULL CHECK (length(inventory_number) > 0) UNIQUE,
    document_id int NOT NULL REFERENCES documents(id)
);

-- subscribers

CREATE TABLE IF NOT EXISTS departments (
    id SERIAL PRIMARY KEY,
    phone_number varchar(255)
);

CREATE TABLE IF NOT EXISTS subscribers (
    id SERIAL PRIMARY KEY,
    first_name varchar(255) NOT NULL CHECK (length(first_name) > 0),
    last_name varchar(255) NOT NULL CHECK (length(last_name) > 0),
    middle_name varchar(255) CHECK (length(middle_name) > 0),
    subscriber_number varchar(50) NOT NULL CHECK (length(subscriber_number) > 0) UNIQUE,
    department_id int NOT NULL REFERENCES departments(id)  
);

-- issues

CREATE TABLE IF NOT EXISTS document_issues (
    id SERIAL PRIMARY KEY,
    issued_at timestamptz NOT NULL,
    returned_at timestamptz CHECK (returned_at > issued_at OR returned_at is null),
    subscriber_id int NOT NULL REFERENCES subscribers(id),
    document_id int NOT NULL REFERENCES documents(id)
);

-- EMPLOYEES

CREATE TABLE IF NOT EXISTS employee_roles (
    id SERIAL PRIMARY KEY,
    name varchar(255) NOT NULL CHECK (length(name) > 0) UNIQUE
);

CREATE TABLE IF NOT EXISTS employees (
    id SERIAL PRIMARY KEY,
    username varchar(255) NOT NULL CHECK (length(username) > 0) UNIQUE,
    password varchar(255) NOT NULL CHECK (length(password) > 0),
    role_id int NOT NULL REFERENCES employee_roles(id)        
);
