const { assert } = require('../utils/assertion')
const db = require('../db')
const bcrypt = require('bcrypt')

const saltRounds = 10

module.exports = class UserController {
    static async createUser(username, password, roleId) {
        assert(username, 'username is required')
        assert(password, 'password is required')
        assert(roleId, 'roleId is required')

        const existingUser = await db.query(
            'SELECT * FROM "user" WHERE user_name = $1',
            [username]
        )

        assert(!existingUser.rowCount.length, 'user already exists')

        const passwordHash = await bcrypt.hash(password, saltRounds)
        await db.query(
            'INSERT INTO "user" (user_name, user_password, user_role_id) VALUES ($1, $2, $3)',
            [username, passwordHash, roleId]
        )
    }

    static async getUser(userId) {
        assert(userId, 'userId is required')

        const user = await db.query(
            'SELECT * FROM "user" WHERE user_id = $1',
            [userId]
        )

        return user.rows[0]
    }
}
