'use strict'

const express = require('express')
const { PORT } = require('./config')

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

app.use(require('body-parser').json({ type: 'application/json' }))

app.get('/', (req, res) => {
    res.send('Hello World!')
})

app.use(require('./routes/auth'))

app.listen(PORT, () => {
    console.log(`Listening at http://localhost:${PORT}`)
})
