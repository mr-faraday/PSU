'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')

const name = 'Rack'

exports.Rack = db.define(name, {
    id: SERIAL,
    rack_number: {
        type: DataTypes.INTEGER,
        allowNull: false,
        unique: true,
        validate: {
            notEmpty: true,
            isInt: true
        }
    }
})
