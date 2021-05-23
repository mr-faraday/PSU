import { API_BASEURL } from '../app/constants'

export default {
    token: null,
    baseUrl: API_BASEURL,
    setToken (jwt) {
        this.token = jwt
    },
    async send (method, path, body) {
        const url = this.baseUrl + path
        const requestInit = {
            headers: {
                'Content-Type': 'application/json'
            },
            method
        }

        if (body) Object.assign(requestInit, { body })

        if (this.token) {
            requestInit.headers.Authorization = `Bearer ${this.token}`
        }

        const request = new Request(url, requestInit)

        const req = await fetch(request)
        req.data = await req.json()

        return req
    },

    async getMostClaimedDocument () {
        return await this.send('GET', '/archive/most-claimed-document')
    },
    async getDocumentsCountBySubject (subject) {
        return await this.send(
            'GET',
            `/archive/document-count-by-subject?subject=${subject}`
        )
    },
    async getEmptyCellsCount () {
        return await this.send('GET', '/archive/empty-cells-count')
    },
    async getDocumentSubjectName (document) {
        return await this.send(
            'GET',
            `/archive/document-subject-name?document=${document}`
        )
    },
    async getDocumentWithLargestCopiesNumber () {
        return await this.send(
            'GET',
            '/archive/document-with-largest-copies-number'
        )
    },
    async getDocumentLastSubscriber (document) {
        return await this.send(
            'GET',
            `/archive/document-last-subscriber?document=${document}`
        )
    },
    async getEmptySpace () {
        return await this.send('GET', '/archive/empty-space')
    },
    async getUnclaimedDocuments () {
        return await this.send('GET', '/archive/unclaimed-documents')
    },
    async getClaimedDocuments () {
        return await this.send('GET', '/archive/claimed-documents')
    }
}
