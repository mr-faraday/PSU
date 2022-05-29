const { assert } = require('../utils/assertion')
const bcrypt = require('bcrypt')
const { User } = require('../db/models/user')

const saltRounds = 10

module.exports.UserController = class UserController {
    static async createUser (login, password, roleId) {
        assert(login, 'login is required')
        assert(password, 'password is required')
        assert(roleId, 'roleId is required')

        const existingUser = await User.findOne({
            where: { login }
        })

        assert(!existingUser, 'user already exists')

        const passwordHash = await bcrypt.hash(password, saltRounds)
        await User.create({
            id: 1,
            login,
            password: passwordHash,
            roleId
        })
    }
}
