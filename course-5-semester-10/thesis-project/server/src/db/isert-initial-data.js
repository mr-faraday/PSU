const { db } = require('.')
const { RoleId } = require('../constants')
const { User } = require('./models/user-role')

exports.insertInitialData = async function () {
    await db.sync({ alter: true })

    await Promise.allSettled([
        User.create({ id: RoleId.ADMIN, name: 'Администратор' }),
        User.create({ id: RoleId.OPERATOR, name: 'Оператор' }),
        User.create({ id: RoleId.MANAGER, name: 'Менеджер' })
    ])
}
