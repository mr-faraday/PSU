import React, { useEffect, useState } from 'react'
import archiveApi from '../../../api/archive-api'

export default {
    name: 'Empty Racks, Sheclfs and Cells',
    href: '/empty-space/',
    component ({ header }) {
        const [loading, setLoading] = useState(false)
        const [data, setData] = useState(null)

        useEffect(() => {
            const fetch = async () => {
                try {
                    setLoading(true)
                    const { data } = await archiveApi.getEmptySpace()

                    const { racks, shelfs, cells } = data.result

                    setData(
                        `Racks: ${racks ?? 'NONE'}\nShelfs: ${
                            shelfs ?? 'NONE'
                        }\nCells: ${cells ?? 'NONE'}`
                    )
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
                <p>Reuslt: {loading ? 'Loading...' : '\n' + data}</p>
            </div>
        )
    }
}
