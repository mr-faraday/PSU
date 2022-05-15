import React, { useEffect, useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Claimed Documents',
    href: '/claimed-documents/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [data, setData] = useState([])

        useEffect(() => {
            const fetch = async () => {
                try {
                    setLoading(true)
                    const { data } = await archiveApi.getClaimedDocuments()

                    setData(data.result)
                } catch (error) {
                    setData([])
                    alert('Error')
                } finally {
                    setLoading(false)
                }
            }

            fetch()
        }, [archiveApi])

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <p>Reuslt: {loading ? 'Loading...' : '\n' + data.join('\n')}</p>
            </div>
        )
    }
}
