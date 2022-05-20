'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Rack } = require('./rack')

const name = 'Shelf'

exports.Shelf = db.define(name, {
    id: SERIAL,
    shelfNumber: {
        type: DataTypes.STRING(50),
        allowNull: false,
        unique: true,
        validate: { notEmpty: true }
    },
    rackId: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Rack,
            key: 'id'
        }
    }
})
