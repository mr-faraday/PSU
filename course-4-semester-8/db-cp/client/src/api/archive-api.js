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
        return await this.send('GET', '/most-claimed-document')
    },
    async getDocumentsCountBySubject (subject) {
        return await this.send(
            'GET',
            `/document-count-by-subject?subject=${subject}`
        )
    },
    async getEmptyCellsCount () {
        return await this.send('GET', '/empty-cells-count')
    },
    async getDocumentSubjectName (document) {
        return await this.send(
            'GET',
            `/document-subject-name?document=${document}`
        )
    },
    async getDocumentWithLargestCopiesNumber () {
        return await this.send(
            'GET',
            '/document-with-largest-copies-number'
        )
    },
    async getDocumentLastSubscriber (document) {
        return await this.send(
            'GET',
            `/document-last-subscriber?document=${document}`
        )
    },
    async getEmptySpace () {
        return await this.send('GET', '/empty-space')
    },
    async getUnclaimedDocuments () {
        return await this.send('GET', '/unclaimed-documents')
    },
    async getClaimedDocuments () {
        return await this.send('GET', '/claimed-documents')
    }
}
