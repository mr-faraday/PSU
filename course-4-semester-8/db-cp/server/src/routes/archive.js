'use strict'

const { query } = require('../db')

const router = require('express').Router()

router.use(require('../middleware/authncticationMiddleware'))

// 1
router.get('/most-claimed-document', async (req, res) => {
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
})

// 2
router.get('/document-count-by-subject', async (req, res) => {
    const { subject } = req.query

    if (!subject) {
        return res.sendStatus(400)
    }

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
})

// 3
router.get('/empty-cells-count', async (req, res) => {})

// 4
router.get('/document-subject-name', async (req, res) => {})

// 5
router.get('/document-with-largest-copies-number', async (req, res) => {})

// 6
router.get('/document-last-subscriber', async (req, res) => {})

// 7
router.get('/empty-space', async (req, res) => {})

// 8
router.get('/unclaimed-documents', async (req, res) => {})

// 9
router.get('/claimed-documents', async (req, res) => {})

module.exports = router
