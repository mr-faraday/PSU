import classNames from 'classnames'
import React from 'react'
import { Link, useLocation } from 'react-router-dom'
import dashboardItems from './dashboard-items'

import './style.scss'

export default function ControlPanel () {
    const location = useLocation()

    const isActive = (route) => location.pathname.includes(route)

    return (
        <nav className="control-pannel">
            <ul>
                {dashboardItems.map((i) => (
                    <li key={i.name}>
                        <Link
                            to={'/dashboard' + i.href}
                            className={classNames('nav-item', {
                                active: isActive(i.href)
                            })}
                        >
                            {i.name}
                        </Link>
                    </li>
                ))}
            </ul>
        </nav>
    )
}
