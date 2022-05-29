'use strict'

const express = require('express')
const { PORT } = require('./config')
const { RoleId } = require('./constants')
const cors = require('cors')
const cookieParser = require('cookie-parser')
const { User } = require('./db/models/user')
const { db } = require('./db')

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
    console.log(`Listening at http://localhost:${PORT}`)

    await db.sync()

    try {
        // const rootUser = await User.findByPk(1)
        // if (!rootUser) {
        //     const rootUser = new User({
        //         id: 1,
        //         login: 'root',
        //         firstName: 'Jhon',
        //         lastName: 'Doe',
        //         roleId: RoleId.ADMIN
        //     })
        //     await rootUser.setPassword('root')
        //     await rootUser.save()
        // }
    } catch (error) {
        console.log(error)
    }
})
