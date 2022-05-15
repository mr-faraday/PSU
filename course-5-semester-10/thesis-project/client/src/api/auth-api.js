import { API_BASEURL } from '../app/constants'

export default {
    async login (...params) {
        return await this._authRequest('/auth/login', ...params)
    },

    async register (...params) {
        return await this._authRequest('/auth/register', ...params)
    },

    async _authRequest (route, username, password) {
        const req = await fetch(API_BASEURL + route, {
            method: 'POST',
            body: JSON.stringify({ username, password }),
            headers: {
                'Content-Type': 'application/json'
            }
        })

        return await req.json()
    }
}
