const { DataTypes } = require('sequelize')

exports.SERIAL = {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true
}
