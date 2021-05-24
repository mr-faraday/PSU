'use strict'

const { query, getClient } = require('../db')

const router = require('express').Router()

router.use(require('../middleware/authenticationMiddleware'))

// 1
router.get('/most-claimed-document', async (req, res, next) => {
    try {
        const result = await query(`
        SELECT document_name FROM document
        INNER JOIN (
            SELECT document_id, COUNT(document_id) AS occurrence FROM document_issue
            GROUP BY document_id
            ORDER BY occurrence DESC
            LIMIT 1
        ) AS res
        ON res.document_id = document.document_id
    `)

        res.json({ result: result.rows[0].document_name })
    } catch (error) {
        next(error)
    }
})

// 2
router.get('/document-count-by-subject', async (req, res, next) => {
    const { subject } = req.query

    if (!subject) {
        return res.sendStatus(400)
    }

    try {
        const result = await query(
            `
            SELECT COUNT(*) FROM
                document LEFT JOIN document_subject AS sub
                ON sub.document_subject_id = document.document_subject_id
            WHERE sub.document_subject_name = $1
            `,
            [subject]
        )

        res.json({ result: result.rows[0].count })
    } catch (error) {
        next(error)
    }
})

// 3
router.get('/empty-cells-count', async (req, res, next) => {
    try {
        const result = await query(`
            SELECT COUNT(*) FROM
                cell LEFT JOIN document AS doc
                ON doc.cell_id = cell.cell_id
            WHERE doc.cell_id IS NULL
        `)

        res.json({ result: result.rows[0].count })
    } catch (error) {
        next(error)
    }
})

// 4
router.get('/document-subject-name', async (req, res, next) => {
    const { document } = req.query

    if (!document) {
        return res.sendStatus(400)
    }

    try {
        const result = await query(
            `
            SELECT document_subject_name FROM
            document_subject INNER JOIN (
                SELECT * FROM document WHERE document_name = $1
            ) AS doc
            ON doc.document_subject_id = document_subject.document_subject_id
            `,
            [document]
        )

        if (result.rowCount === 0) {
            return res.sendStatus(404)
        }

        res.json({ result: result.rows[0].document_subject_name })
    } catch (error) {
        next(error)
    }
})

// 5
router.get('/document-with-largest-copies-number', async (req, res, next) => {
    try {
        const result = await query(`
        SELECT document_name FROM document
        INNER JOIN (
            SELECT document_id, COUNT(document_id) AS occurrence FROM document_copy
            GROUP BY document_id
            ORDER BY occurrence DESC
            LIMIT 1
        ) AS res
        ON res.document_id = document.document_id
    `)

        res.json({ result: result.rows[0].document_name })
    } catch (error) {
        next(error)
    }
})

// 6
router.get('/document-last-subscriber', async (req, res, next) => {
    const { document } = req.query

    if (!document) {
        return res.sendStatus(400)
    }

    try {
        const result = await query(
            `
            SELECT first_name, last_name, middle_name FROM
            subscriber INNER JOIN (
                SELECT subscriber_id, issued_at FROM document_issue INNER JOIN (
                    SELECT document_id FROM document WHERE document_name = $1
                ) AS doc
                ON doc.document_id = document_issue.document_id
            ) AS issue
            ON subscriber.subscriber_id = issue.subscriber_id
            ORDER BY issued_at DESC
            LIMIT 1
            `,
            [document]
        )

        if (result.rowCount === 0) {
            return res.sendStatus(404)
        }

        const { first_name, last_name, middle_name } = result.rows[0]

        res.json({ result: `${first_name} ${middle_name} ${last_name}` })
    } catch (error) {
        next(error)
    }
})

// 7
router.get('/empty-space', async (req, res, next) => {
    try {
        const client = await getClient()

        const [rackRes, shelfRes, cellRes] = await Promise.all([
            client.query(`
                SELECT COUNT(*) FROM (
                    SELECT rack_id FROM rack
                    EXCEPT
                    (SELECT rack_id FROM shelf)
                ) AS res
            `),
            client.query(`
                SELECT COUNT(*) FROM (
                    SELECT shelf_id FROM shelf
                    EXCEPT
                    (SELECT shelf_id FROM cell)
                ) AS res
            `),
            client.query(`
                SELECT COUNT(*) FROM
                    cell LEFT JOIN document AS doc
                    ON doc.cell_id = cell.cell_id
                WHERE doc.cell_id IS NULL
            `)
        ])

        client.release()

        if (
            rackRes.rowCount === 0 ||
            shelfRes.rowCount === 0 ||
            cellRes.rowCount === 0
        ) {
            return res.sendStatus(500)
        }

        res.json({
            result: {
                racks: rackRes.rows[0].count,
                shelfs: shelfRes.rows[0].count,
                cells: cellRes.rows[0].count
            }
        })
    } catch (error) {
        next(error)
    }
})

// 8
router.get('/unclaimed-documents', async (req, res, next) => {
    try {
        const result = await query(`
            SELECT document_name FROM document RIGHT JOIN
            (
                SELECT document_id FROM document_issue
                EXCEPT
                (SELECT document_id FROM document_issue WHERE issued_at > now() - interval '3 year')
            ) AS res ON res.document_id = document.document_id
        `)

        res.json({ result: result.rows.map((row) => row.document_name) })
    } catch (error) {
        next(error)
    }
})

// 9
router.get('/claimed-documents', async (req, res, next) => {
    try {
        const result = await query(`
            SELECT document_name FROM document RIGHT JOIN
            (
                SELECT document_id, returned_at FROM document_issue WHERE returned_at is null
            ) AS res ON res.document_id = document.document_id
        `)

        res.json({ result: result.rows.map((row) => row.document_name) })
    } catch (error) {
        next(error)
    }
})

module.exports = router
