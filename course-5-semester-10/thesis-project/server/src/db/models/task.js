'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Client } = require('./client')
const { Shelf } = require('./shelf')
const { TaskStatus } = require('./task-status')

const name = 'Task'

exports.Task = db.define(name, {
    id: SERIAL,
    cargoId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: 'Cargo',
            key: 'id'
        }
    },
    statusId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: TaskStatus,
            key: 'id'
        }
    },

    sourceShelfId: {
        type: DataTypes.INTEGER,
        references: {
            model: Shelf,
            key: 'id'
        }
    },
    sourcePosition: {
        type: DataTypes.INTEGER,
        allowNull: false
    },
    targetShelfId: {
        type: DataTypes.INTEGER,
        references: {
            model: Shelf,
            key: 'id'
        }
    },
    targetPosition: {
        type: DataTypes.INTEGER,
        allowNull: false
    },

    createdAt: {
        type: DataTypes.DATE,
        allowNull: false
    },
    updatedAt: {
        type: DataTypes.DATE,
        allowNull: false
    },
    createdByClientId: {
        type: DataTypes.INTEGER,
        references: {
            model: Client,
            key: 'id'
        }
    }
})
