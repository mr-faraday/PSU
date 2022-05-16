'use strict'

const express = require('express')
const { PORT } = require('./config')
const { RoleId } = require('./constants')
const UserController = require('./controllers/user-controller')
const { query } = require('./db')

const app = express()

app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*')
    res.setHeader(
        'Access-Control-Allow-Methods',
        'GET, POST, OPTIONS, PUT, PATCH, DELETE'
    )
    res.setHeader(
        'Access-Control-Allow-Headers',
        'Access-Control-Allow-Headers, Origin, Accept, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers, Authorization'
    )
    res.setHeader('Access-Control-Allow-Credentials', true)

    next()
})
app.options('/*', (req, res) => res.sendStatus(200))

app.use(require('body-parser').json({ type: 'application/json' }))

app.get('/', (req, res) => {
    res.send('Hello World!')
})

app.use('/auth', require('./routes/auth'))
app.use('/archive', require('./routes/archive'))
app.use('/user', require('./routes/user'))

app.use((error, req, res, next) => {
    console.warn(error)
    return res.status(500).json({ error: error.toString() })
})

app.listen(PORT, async () => {
    console.log(`Listening at http://localhost:${PORT}`)

    const rootUser = await query('SELECT * FROM "user" WHERE user_id = 1')
    if (rootUser.rowCount === 0) {
        await UserController.createUser('root', 'root', RoleId.ADMIN)
    }
})
