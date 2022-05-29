'use strict'

const express = require('express')
const { PORT } = require('./config')
const cors = require('cors')
const cookieParser = require('cookie-parser')
const { initDb } = require('./db')

const app = express()

app.use(
    cors({
        credentials: true,
        origin: (origin, callback) => {
            callback(null, true)
            // callback(new Error('Not allowed by CORS'))
        }
    })
)

app.use(cookieParser())

app.use(require('body-parser').json({ type: 'application/json' }))

app.get('/', (req, res) => {
    res.send('Hello World!')
})

app.use('/auth', require('./routes/auth'))
app.use('/archive', require('./routes/archive'))
app.use('/user', require('./routes/user'))

app.use((error, req, res, next) => {
    console.warn(error)
    return res.status(500).json({ error: error.message })
})

app.listen(PORT, async () => {
    await initDb().catch(console.error)

    console.log(`Listening at http://localhost:${PORT}`)
})
