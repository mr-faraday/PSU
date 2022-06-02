const { db } = require('.')
const { UserRoleId, TaskStatusId } = require('../constants')
const { Rack } = require('./models/rack')
const { Shelf } = require('./models/shelf')
const { TaskStatus } = require('./models/task-status')
const { User } = require('./models/user')
const { UserRole } = require('./models/user-role')

const createUsers = async () => {
    const admin = new User({
        login: 'admin',
        firstName: 'Jhon',
        lastName: 'Doe',
        roleId: UserRoleId.ADMIN
    })
    await admin.setPassword('1234')
    await admin.save()

    const manager = new User({
        login: 'manager',
        firstName: 'Jane',
        lastName: 'Doe',
        roleId: UserRoleId.MANAGER
    })
    await manager.setPassword('1234')
    await manager.save()

    const operator = new User({
        login: 'operator',
        firstName: 'Chris',
        lastName: 'Pratt',
        roleId: UserRoleId.OPERATOR
    })
    await operator.setPassword('1234')
    await operator.save()
}

exports.insertInitialData = async function () {
    await db.sync({ alter: true })

    // initialize criteria
    const rootUser = await User.findByPk(1)
    if (rootUser) return

    await Promise.allSettled([
        UserRole.create({ id: UserRoleId.ADMIN, name: 'Администратор' }),
        UserRole.create({ id: UserRoleId.OPERATOR, name: 'Оператор' }),
        UserRole.create({ id: UserRoleId.MANAGER, name: 'Менеджер' }),

        TaskStatus.create({ id: TaskStatusId.NEW, name: 'Новая' }),
        TaskStatus.create({ id: TaskStatusId.DONE, name: 'Выполнена' }),
        TaskStatus.create({ id: TaskStatusId.CANCELED, name: 'Отменена' }),

        Rack.create({ levelsHeight: 3, postionRow: 1 }),
        Rack.create({ levelsHeight: 3, postionRow: 2 }),
        Rack.create({ levelsHeight: 3, postionRow: 3 }),

        Shelf.create({ positionQuantity: 10, levelHeight: 1, rackId: 1 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 2, rackId: 1 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 3, rackId: 1 }),

        Shelf.create({ positionQuantity: 10, levelHeight: 1, rackId: 2 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 2, rackId: 2 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 3, rackId: 2 }),

        Shelf.create({ positionQuantity: 10, levelHeight: 1, rackId: 3 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 2, rackId: 3 }),
        Shelf.create({ positionQuantity: 10, levelHeight: 3, rackId: 3 })
    ])

    await createUsers()
}
