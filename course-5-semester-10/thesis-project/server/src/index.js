'use strict'

const express = require('express')
const { PORT } = require('./config')
const cookieParser = require('cookie-parser')

const app = express()

app.use(cookieParser())

app.use(require('body-parser').json({ type: 'application/json' }))

app.get('/', (req, res) => {
    res.send('Hello World!')
})

app.use('/auth', require('./routes/auth'))
app.use('/user', require('./routes/user'))
app.use('/settings', require('./routes/settings'))
app.use('/employees', require('./routes/employees'))

app.use((error, req, res, next) => {
    console.warn(error)
    return res.status(500).json({ error: error.message })
})

app.listen(PORT, async () => {
    await require('./db').initDb().catch(console.error)

    console.log()
    console.log(`Listening at http://localhost:${PORT}`)
})
