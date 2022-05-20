const { assert } = require('../utils/assertion')
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
    }
}
