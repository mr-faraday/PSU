import React, { useEffect, useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Claimed Documents',
    href: '/claimed-documents/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [data, setData] = useState(null)

        useEffect(() => {
            const fetch = async () => {
                try {
                    setLoading(true)
                    const result = await archiveApi.REQUEST()

                    setData(result)
                } catch (error) {
                    setData('Error')
                } finally {
                    setLoading(false)
                }
            }

            fetch()
        }, [archiveApi])

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <p>Reuslt: {loading ? 'Loading...' : data}</p>
            </div>
        )
    }
}
