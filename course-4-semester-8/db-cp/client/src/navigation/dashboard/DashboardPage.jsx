import React from 'react'
import { Route } from 'react-router'
import ControlPanel from '../../components/dashboard/ControlPanel'
import dashboardItems from '../../components/dashboard/dashboard-items'

import './style.scss'

export default function DashboardPage () {
    return (
        <div className="dashboard-page">
            <ControlPanel />

            <Route exact path="/dashboard/">
                <div className="operation-window">
                    <h2>Dashboard</h2>

                    <p>Select operation in side menu</p>
                </div>
            </Route>

            {dashboardItems.map((i) => (
                <Route key={i.name} exact path={'/dashboard' + i.href}>
                    <i.component header={i.name} />
                </Route>
            ))}

            {/* <Route exact path="/dashboard/most-claimed/"></Route>
            <Route exact path="/dashboard/documnets-conunt-by-subject/"></Route>
            <Route exact path="/dashboard/empty-cells/"></Route>
            <Route exact path="/dashboard/document-subject-by-name/"></Route>
            <Route exact path="/dashboard/most-copies-document/"></Route>
            
            <Route exact path="/dashboard/last-subscriber-by-document/"></Route>
            <Route exact path="/dashboard/empty-space/"></Route>
            <Route exact path="/dashboard/unclaimed-document/s"></Route>
            <Route exact path="/dashboard/claimed-documents/"></Route> */}
        </div>
    )
}
