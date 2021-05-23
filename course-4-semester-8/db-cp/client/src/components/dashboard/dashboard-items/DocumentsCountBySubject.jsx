import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Document Count by Subject',
    href: '/documnets-conunt-by-subject/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [subject, setSubject] = useState('')
        const [count, setCount] = useState(null)

        const fetch = async () => {
            try {
                setLoading(true)
                const { data } = await archiveApi.getDocumentsCountBySubject(
                    subject
                )

                setCount(data.result)
            } catch (error) {
                setCount('Error')
            } finally {
                setLoading(false)
            }
        }

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <input
                    value={subject}
                    placeholder="Subject..."
                    onChange={(e) => setSubject(e.target.value)}
                />
                <button onClick={fetch}>Submit</button>
                <p>Reuslt: {loading ? 'Loading...' : count}</p>
            </div>
        )
    }
}
