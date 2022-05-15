import React, { useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Last Subscripber that Tooked Document',
    href: '/last-subscriber/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [document, setDocument] = useState('')
        const [data, setData] = useState(null)

        const fetch = async (e) => {
            e.preventDefault()

            if (!document) return

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

                <form onSubmit={fetch}>
                    <input
                        value={document}
                        onChange={(e) => setDocument(e.target.value)}
                    />
                    <input type="submit" value="Submit" />
                </form>
                <p>Reuslt: {loading ? 'Loading...' : data}</p>
            </div>
        )
    }
}
