import React, { useEffect, useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Most Claimed Document',
    href: '/most-claimed/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [document, setDocument] = useState(null)

        useEffect(() => {
            const fetch = async () => {
                try {
                    setLoading(true)
                    const result = await archiveApi.REQUEST()

                    setDocument(result)
                } catch (error) {
                    setDocument('Error')
                } finally {
                    setLoading(false)
                }
            }

            fetch()
        }, [archiveApi])

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <p>Reuslt: {loading ? 'Loading...' : document}</p>
            </div>
        )
    }
}
