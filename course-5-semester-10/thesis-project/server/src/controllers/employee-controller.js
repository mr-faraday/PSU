const { assert } = require('../utils/assertion')
const bcrypt = require('bcrypt')
const { Employee } = require('../db/models/employee')

const saltRounds = 10

module.exports.EmployeeController = class EmployeeController {
    static async createEmployee (login, password, roleId) {
        assert(login, 'login is required')
        assert(password, 'password is required')
        assert(roleId, 'roleId is required')

        const existingEmployee = await Employee.findOne({
            where: { login }
        })

        assert(!existingEmployee, 'user already exists')

        const passwordHash = await bcrypt.hash(password, saltRounds)
        await Employee.create({
            id: 1,
            login,
            password: passwordHash,
            roleId
        })
    }
}
