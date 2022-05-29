const fs = require('fs')
const path = require('path')

exports.importModels = function () {
    for (const file of fs.readdirSync(path.join(__dirname, 'models'))) {
        if (file.indexOf('.') !== 0 && file.slice(-3) === '.js') {
            require(path.join(__dirname, '/models/', file))
        }
    }
}
