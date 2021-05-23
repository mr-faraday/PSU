const { query } = require('../db')
const bcrypt = require('bcrypt')
const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')

const saltRounds = 10

const router = require('express').Router()

router.post('/auth/login', async (req, res) => {
    const { username, password } = req.body

    if (!username || !password) {
        return res.sendStatus(400)
    }

    const existingUser = await query(
        'SELECT operator_password FROM operator WHERE operator_name = $1',
        [username]
    )
 
    if (existingUser.rowCount === 0) {
        return res.sendStatus(404)
    }

    const hash = existingUser.rows[0].operator_password

    if (!(await bcrypt.compare(password, hash))) {
        return res.sendStatus(401)
    }

    const token = jwt.sign({ user: username }, JWT_SECRET)

    res.json({ jwt: token })
})

router.post('/auth/register', async (req, res) => {
    const { username, password } = req.body

    if (!username || !password) {
        return res.sendStatus(400)
    }

    const existingUser = await query(
        'SELECT operator_name FROM operator WHERE operator_name = $1',
        [username]
    )

    if (existingUser.rowCount > 0) {
        return res.sendStatus(409)
    }

    const passwordHash = await bcrypt.hash(password, saltRounds)
    await query(
        'INSERT INTO operator (operator_name, operator_password) VALUES ($1, $2)',
        [username, passwordHash]
    )

    const token = jwt.sign({ user: username }, JWT_SECRET)

    res.json({ jwt: token })
})

module.exports = router
