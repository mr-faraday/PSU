import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Document Subject by Name',
    href: '/document-subject-by-name/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [name, setName] = useState('')
        const [subject, setSubject] = useState(null)

        const fetch = async () => {
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
                <input
                    value={name}
                    placeholder="Document name..."
                    onChange={(e) => setName(e.target.value)}
                />
                <button onClick={fetch}>Submit</button>
                <p>Reuslt: {loading ? 'Loading...' : subject}</p>
            </div>
        )
    }
}
