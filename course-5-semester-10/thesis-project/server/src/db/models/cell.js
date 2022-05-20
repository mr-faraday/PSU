'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Shelf } = require('./shelf')

const name = 'Cell'

exports.Shelf = db.define(name, {
    id: SERIAL,
    cellNumber: {
        type: DataTypes.STRING(50),
        allowNull: false,
        unique: true,
        validate: { notEmpty: true }
    },
    shelfId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Shelf,
            key: 'id'
        }
    }
})
