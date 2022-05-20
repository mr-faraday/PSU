'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { EmployeeRole } = require('./employee-role')

const name = 'Employee'

exports.Employee = db.define(
    name,
    {
        id: SERIAL,
        username: {
            type: DataTypes.STRING(255),
            allowNull: false,
            unique: true,
            validate: { notEmpty: true }
        },
        password: {
            type: DataTypes.STRING(255),
            allowNull: false,
            validate: { notEmpty: true }
        },
        roleId: {
            type: DataTypes.INTEGER,
            allowNull: false,
            references: {
                model: EmployeeRole,
                key: 'id'
            }
        }
    }
)
