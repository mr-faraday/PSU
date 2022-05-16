module.exports.assert = function assert(value, message) {
    if (!value) {
        throw new AssertionError(message || 'No message')
    }
}

class AssertionError extends Error {
    constructor(message) {
        super(message)
        Object.setPrototypeOf(this, AssertionError.prototype)
    }
}
