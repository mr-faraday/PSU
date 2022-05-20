const { assert } = require('../utils/assertion')
const db = require('../db')
const bcrypt = require('bcrypt')
const { Employee } = require('../db/models/employees')

const saltRounds = 10

module.exports.EmployeeController = class EmployeeController {
    static async createEmployee (username, password, roleId) {
        assert(username, 'username is required')
        assert(password, 'password is required')
        assert(roleId, 'roleId is required')

        const existingEmployee = await Employee.findOne({
            where: { username }
        })

        assert(!existingEmployee, 'user already exists')

        const passwordHash = await bcrypt.hash(password, saltRounds)
        await Employee.create({
            id: 1,
            username,
            password: passwordHash,
            roleId
        })
        // await db.query(
        //     'INSERT INTO "user" (user_name, user_password, user_role_id) VALUES ($1, $2, $3)',
        //     [username, passwordHash, roleId]
        // )
    }

    static async getEmployee (userId) {
        assert(userId, 'userId is required')

        const user = await db.query('SELECT * FROM "user" WHERE user_id = $1', [
            userId
        ])

        return user.rows[0]
    }
}
