import { API_BASEURL } from '../app/constants'

export default {
    token: null,
    baseUrls: API_BASEURL,
    setToken (jwt) {
        this.token = jwt
    },
    async send (method, path, body) {
        const url = this.baseUrl + path
        const requestInit = { headers: {}, method }

        if (body) Object.assign(requestInit, { body })

        if (this.token) {
            Object.assign(requestInit.headers, {
                authorization: `Bearer ${this.token}`
            })
        }

        const request = new Request(url, requestInit)

        const req = await fetch(request)
        req.data = await req.json()

        return req
    },

    async getMostClaimedDocument () {
        return await this.send('GET', '/get-most-claimed-document')
    },
    getDocumentsCountBySubject () {}
}
