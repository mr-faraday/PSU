-- set session my.number_of_issuess = '21589';
set session my.number_of_issuess = '5000';

CREATE OR REPLACE PROCEDURE create_issues()
LANGUAGE plpgsql
AS $$
DECLARE
    issues_length INT := current_setting('my.number_of_issuess')::int;
    i INT := 0;
    doc_id INT;
	sub_id INT;
    p_issued_at timestamptz;
    return_date timestamptz;
    p_returned_at timestamptz;
BEGIN
	RAISE INFO 'Filling Issues ...';
	
    <<issues_loop>> LOOP
        IF i > issues_length THEN
            EXIT issues_loop;
        END IF;

        p_issued_at := random_timestamp(timestamptz '2007-05-22T22:14:12Z');
        return_date := TO_TIMESTAMP(EXTRACT(EPOCH FROM p_issued_at) + floor(random() * 3600 * 24 * 180));

        IF now() > return_date THEN
            p_returned_at := return_date;
        ELSE
            p_returned_at := null;
        END IF;

        SELECT document_id INTO doc_id FROM
		(
			SELECT id as document_id FROM documents AS doc
			WHERE
				p_issued_at > doc.arrived_at
			EXCEPT
			SELECT document_id FROM document_issues
			WHERE
				p_issued_at > document_issues.issued_at AND
				(p_issued_at < document_issues.returned_at OR p_issued_at IS NULL)
			
		) AS res
		ORDER BY RANDOM()
		LIMIT 1;

        IF doc_id IS NULL
		THEN
            RAISE EXCEPTION 'No available documents for issuing, restart script manually';
        END IF;
		
		SELECT id as subscriber_id INTO sub_id FROM subscribers ORDER BY RANDOM() LIMIT 1;

        INSERT INTO document_issues (issued_at, returned_at, subscriber_id, document_id)
            VALUES (p_issued_at, p_returned_at, sub_id, doc_id);

        i := i + 1;
    END LOOP issues_loop;
END
$$;

CALL create_issues();
DROP PROCEDURE IF EXISTS create_issues;
