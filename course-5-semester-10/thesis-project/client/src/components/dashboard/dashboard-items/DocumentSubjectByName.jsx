import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Document Subject by Name',
    href: '/document-subject-by-name/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [name, setName] = useState('')
        const [subject, setSubject] = useState(null)

        const fetch = async (e) => {
            e.preventDefault()

            if (!name) return

            try {
                setLoading(true)
                const { data } = await archiveApi.getDocumentSubjectName(name)

                setSubject(data.result)
            } catch (error) {
                setSubject('Error')
            } finally {
                setLoading(false)
            }
        }

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <form onSubmit={fetch}>
                    <input
                        value={name}
                        placeholder="Document name..."
                        onChange={(e) => setName(e.target.value)}
                    />
                    <input type="submit" value="Submit" />
                </form>
                <p>Reuslt: {loading ? 'Loading...' : subject}</p>
            </div>
        )
    }
}
