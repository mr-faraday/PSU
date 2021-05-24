import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Document Count by Subject',
    href: '/documnets-conunt-by-subject/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [subject, setSubject] = useState('')
        const [count, setCount] = useState(null)

        const fetch = async (e) => {
            e.preventDefault()

            if (!subject) return

            try {
                setLoading(true)
                const { data } = await archiveApi.getDocumentsCountBySubject(
                    subject
                )

                setCount(String(data.result))
            } catch (error) {
                setCount('Error')
            } finally {
                setLoading(false)
            }
        }

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <form onSubmit={fetch}>
                    <input
                        value={subject}
                        placeholder="Subject..."
                        onChange={(e) => setSubject(e.target.value)}
                    />
                    <input type="submit" value="Submit" />
                </form>
                <p>Reuslt: {loading ? 'Loading...' : count}</p>
            </div>
        )
    }
}
