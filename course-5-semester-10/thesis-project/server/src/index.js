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

app.use('/auth', require('./routers/auth'))
app.use('/user', require('./routers/user'))
app.use('/settings', require('./routers/settings'))
app.use('/employees', require('./routers/employees'))
app.use('/clients', require('./routers/clients'))
app.use('/cargos', require('./routers/cargos'))

app.use((error, req, res, next) => {
    console.warn(error)
    return res.status(500).json({ error: error.message })
})

app.listen(PORT, async () => {
    await require('./db').initDb().catch(console.error)

    console.log()
    console.log(`Listening at http://localhost:${PORT}`)
})
