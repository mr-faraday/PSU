import { API_BASEURL } from '../app/constants'

export default {
    async login (...params) {
        return await this._authRequest('/auth/login', ...params)
    },

    async register (...params) {
        return await this._authRequest('/auth/login', ...params)
    },

    async _authRequest (route, username, password) {
        const req = await fetch(API_BASEURL, {
            url: route,
            method: 'POST',
            body: JSON.stringify({ username, password })
        })

        return await req.json()
    }
}
