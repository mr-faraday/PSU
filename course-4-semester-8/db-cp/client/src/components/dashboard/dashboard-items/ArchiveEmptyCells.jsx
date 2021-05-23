import React, { useEffect, useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Archive Empty Cells',
    href: '/empty-cells/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [count, setCount] = useState(null)

        useEffect(() => {
            const fetch = async () => {
                try {
                    setLoading(true)
                    const result = await archiveApi.REQUEST()

                    setCount(result)
                } catch (error) {
                    setCount('Error')
                } finally {
                    setLoading(false)
                }
            }

            fetch()
        }, [archiveApi])

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <p>Reuslt: {loading ? 'Loading...' : count}</p>
            </div>
        )
    }
}
