import { API_URL } from '@/config'
import axios from 'axios'

// export default {
//     token: null,
//     baseUrl: API_BASEURL,
//     setToken (jwt) {
//         this.token = jwt
//     },
//     async send (method, path, body) {
//         const url = this.baseUrl + path
//         const requestInit = {
//             headers: {
//                 'Content-Type': 'application/json'
//             },
//             method
//         }

//         if (body) Object.assign(requestInit, { body })

//         if (this.token) {
//             requestInit.headers.Authorization = `Bearer ${this.token}`
//         }

//         const request = new Request(url, requestInit)

//         const req = await fetch(request)
//         req.data = await req.json()

//         return req
//     },

//     // 1
//     async getMostClaimedDocument () {
//         return await this.send('GET', '/archive/most-claimed-document')
//     },
//     // 2
//     async getDocumentsCountBySubject (subject) {
//         return await this.send(
//             'GET',
//             `/archive/document-count-by-subject?subject=${subject}`
//         )
//     },
//     // 3
//     async getEmptyCellsCount () {
//         return await this.send('GET', '/archive/empty-cells-count')
//     },
//     // 4
//     async getDocumentSubjectName (document) {
//         return await this.send(
//             'GET',
//             `/archive/document-subject-name?document=${document}`
//         )
//     },
//     // 5
//     async getDocumentWithLargestCopiesNumber () {
//         return await this.send(
//             'GET',
//             '/archive/document-with-largest-copies-number'
//         )
//     },
//     // 6
//     async getDocumentLastSubscriber (document) {
//         return await this.send(
//             'GET',
//             `/archive/document-last-subscriber?document=${document}`
//         )
//     },
//     // 7
//     async getEmptySpace () {
//         return await this.send('GET', '/archive/empty-space')
//     },
//     // 8
//     async getUnclaimedDocuments () {
//         return await this.send('GET', '/archive/unclaimed-documents')
//     },
//     // 9
//     async getClaimedDocuments () {
//         return await this.send('GET', '/archive/claimed-documents')
//     }
// }

const instance = axios.create({
  baseURL: `${API_URL}/archive`,
  withCredentials: true,
})

export default class ArchiveApi {
  // 1
  static async getMostClaimedDocument() {
    return await instance.get('/most-claimed-document')
  }

  // 2
  static async getDocumentsCountBySubject(subject) {
    return await instance.get(`/document-count-by-subject`, { params: { subject } })
  }

  // 3
  static async getEmptyCellsCount() {
    return await instance.get('/empty-cells-count')
  }

  //4
  static async getDocumentSubjectName(document) {
    return await instance.get(`/document-subject-name`, { params: { document } })
  }

  // 5
  static async getDocumentWithLargestCopiesNumber() {
    return await instance.get('/document-with-largest-copies-number')
  }

  // 6
  static async getDocumentLastSubscriber(document) {
    return await instance.get(`/document-last-subscriber`, { params: { document } })
  }

  // 7
  static async getEmptySpace() {
    return await instance.get('/empty-space')
  }

  // 8
  static async getUnclaimedDocuments() {
    return await instance.get('/unclaimed-documents')
  }

  // 9
  static async getClaimedDocuments() {
    return await instance.get('/claimed-documents')
  }
}
