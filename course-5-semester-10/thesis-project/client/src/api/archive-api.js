import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/archive` })

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
