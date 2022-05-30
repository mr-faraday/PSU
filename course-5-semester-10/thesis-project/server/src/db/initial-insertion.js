const { db } = require('.')
const { UserRoleId, TaskStatusId } = require('../constants')
const { Rack } = require('./models/rack')
const { Shelf } = require('./models/shelf')
const { TaskStatus } = require('./models/task-status')
const { User } = require('./models/user')
const { UserRole } = require('./models/user-role')

const createRootUser = async () => {
    try {
        const rootUser = new User({
            id: 1,
            login: 'root',
            firstName: 'Jhon',
            lastName: 'Doe',
            roleId: UserRoleId.ADMIN
        })
        await rootUser.setPassword('root')
        await rootUser.save()
    } catch (error) {
        console.log(error)
    }
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

        TaskStatus.create({ id: TaskStatusId.NEW, name: 'Новое' }),
        TaskStatus.create({ id: TaskStatusId.IN_PROGRESS, name: 'В работе' }),
        TaskStatus.create({ id: TaskStatusId.DONE, name: 'Выполнено' }),
        TaskStatus.create({ id: TaskStatusId.CANCELED, name: 'Отменено' }),

        Rack.create({ levelsHeight: 3, postionRow: 1 }),
        Rack.create({ levelsHeight: 3, postionRow: 2 }),
        Rack.create({ levelsHeight: 3, postionRow: 3 }),

        Shelf.create({ long: 10, levelHeight: 1, rackId: 1 }),
        Shelf.create({ long: 10, levelHeight: 2, rackId: 1 }),
        Shelf.create({ long: 10, levelHeight: 3, rackId: 1 }),

        Shelf.create({ long: 10, levelHeight: 1, rackId: 2 }),
        Shelf.create({ long: 10, levelHeight: 2, rackId: 2 }),
        Shelf.create({ long: 10, levelHeight: 3, rackId: 2 }),

        Shelf.create({ long: 10, levelHeight: 1, rackId: 3 }),
        Shelf.create({ long: 10, levelHeight: 2, rackId: 3 }),
        Shelf.create({ long: 10, levelHeight: 3, rackId: 3 })
    ])

    await createRootUser()
}
