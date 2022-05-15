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

    // 1
    async getMostClaimedDocument () {
        return await this.send('GET', '/archive/most-claimed-document')
    },
    // 2
    async getDocumentsCountBySubject (subject) {
        return await this.send(
            'GET',
            `/archive/document-count-by-subject?subject=${subject}`
        )
    },
    // 3
    async getEmptyCellsCount () {
        return await this.send('GET', '/archive/empty-cells-count')
    },
    // 4
    async getDocumentSubjectName (document) {
        return await this.send(
            'GET',
            `/archive/document-subject-name?document=${document}`
        )
    },
    // 5
    async getDocumentWithLargestCopiesNumber () {
        return await this.send(
            'GET',
            '/archive/document-with-largest-copies-number'
        )
    },
    // 6
    async getDocumentLastSubscriber (document) {
        return await this.send(
            'GET',
            `/archive/document-last-subscriber?document=${document}`
        )
    },
    // 7
    async getEmptySpace () {
        return await this.send('GET', '/archive/empty-space')
    },
    // 8
    async getUnclaimedDocuments () {
        return await this.send('GET', '/archive/unclaimed-documents')
    },
    // 9
    async getClaimedDocuments () {
        return await this.send('GET', '/archive/claimed-documents')
    }
}
