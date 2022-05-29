'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Client } = require('./client')

const name = 'Cargo'

exports.Cargo = db.define(name, {
    id: SERIAL,
    clientId: {
        type: DataTypes.INTEGER,
        references: {
            model: Client,
            key: 'id'
        }
    },
    weight: {
        type: DataTypes.INTEGER,
        allowNull: false
    },
    arrived_at: {
        type: DataTypes.DATE,
        allowNull: false
    }
})
