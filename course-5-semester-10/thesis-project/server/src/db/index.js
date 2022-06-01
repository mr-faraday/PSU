'use strict'

const { Sequelize } = require('sequelize')
const {
    POSTGRES_USER,
    POSTGRES_PASSWORD,
    POSTGRES_DB,
    POSTGRES_HOST
} = require('../config')

exports.db = new Sequelize({
    host: POSTGRES_HOST,
    port: 5432,
    dialect: 'postgres',
    username: POSTGRES_USER,
    password: POSTGRES_PASSWORD,
    database: POSTGRES_DB,
    define: {
        timestamps: false,
        underscored: true
    }
})

exports.initDb = async () => {
    require('./import-models').importModels()
    await require('./initial-insertion').insertInitialData()

    const { Rack } = require('./models/rack')
    const { Shelf } = require('./models/shelf')
    const { Cargo } = require('./models/cargo')
    const { CargoPlacement } = require('./models/cargo-placement')
    const { Task } = require('./models/task')
    const { TaskStatus } = require('./models/task-status')
    const { Client } = require('./models/client')
    const { User } = require('./models/user')
    const { UserRole } = require('./models/user-role')

    Rack.hasMany(Shelf, { foreignKey: 'rackId' })
    // Shelf.belongsTo(Rack)

    // Shelf.hasMany(CargoPlacement, { foreignKey: 'shelfId' })
    CargoPlacement.belongsTo(Shelf)
    // CargoPlacement.belongsTo(Shelf)

    // Shelf.hasMany(Task, [
    //     { as: 'source', foreignKey: 'sourceShelfId' },
    //     { as: 'target', foreignKey: 'targetShelfId' }
    // ])
    // Task.belongsTo(Shelf)

    Cargo.hasOne(CargoPlacement, { foreignKey: 'cargoId' })
    // CargoPlacement.belongsTo(Cargo)

    Client.hasMany(Cargo, { as: 'cargoes', foreignKey: 'clientId' })
    // Cargo.belongsTo(Client)

    Cargo.hasMany(Task, { as: 'tasks', foreignKey: 'cargoId' })
    // Task.belongsTo(Cargo)

    TaskStatus.hasMany(Task, { foreignKey: 'statusId' })
    // TaskStatus.belongsTo(TaskStatus)

    User.hasMany(Task, { foreignKey: 'createdByUserId' })
    // Task.belongsTo(User)

    UserRole.hasMany(User, { as: 'users', foreignKey: 'roleId' })
    // User.belongsTo(UserRole)
}
