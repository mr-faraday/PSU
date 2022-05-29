'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')

const name = 'TaskStatus'

exports.TaskStatus = db.define(name, {
    id: SERIAL,
    name: {
        type: DataTypes.STRING(255),
        allowNull: false,
        unique: true,
        validate: { notEmpty: true }
    }
})
