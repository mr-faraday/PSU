import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Last Subscripber that Tooked Document',
    href: '/last-subscriber/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [document, setDocument] = useState('')
        const [data, setData] = useState(null)

        const fetch = async () => {
            try {
                setLoading(true)
                const { data } = await archiveApi.getDocumentLastSubscriber(
                    document
                )

                setData(data.result)
            } catch (error) {
                setData('Error')
            } finally {
                setLoading(false)
            }
        }

        return (
            <div className="operation-window">
                <h2>{header}</h2>
                <input
                    value={document}
                    onChange={(e) => setDocument(e.target.value)}
                />
                <button onClick={fetch}>Submit</button>
                <p>Reuslt: {loading ? 'Loading...' : data}</p>
            </div>
        )
    }
}
