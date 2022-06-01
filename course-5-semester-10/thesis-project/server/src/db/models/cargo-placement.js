'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Cargo } = require('./cargo')
const { Shelf } = require('./shelf')

const name = 'CargoPlacement'

exports.CargoPlacement = db.define(name, {
    id: SERIAL,
    cargoId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Cargo,
            key: 'id'
        }
    },
    shelfId: {
        type: DataTypes.INTEGER,
        allowNull: true,
        references: {
            model: Shelf,
            key: 'id'
        }
    },
    position: {
        type: DataTypes.INTEGER,
        allowNull: true
    }
})
