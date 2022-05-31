import { UserRoleId } from '@/constants'

const dashboardItems = [
  {
    name: 'Управелние персоналом',
    href: '/dashboard/employees',
    component: 'EmployeesView',
    meta: {
      title: 'Управелние персоналом',
    },
    roles: [UserRoleId.ADMIN],
  },
  {
    name: 'Клиенты',
    href: '/dashboard/clients',
    component: 'ClientsView',
    meta: {
      title: 'Клиенты',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER],
  },
  {
    name: 'Задачи по приёму/распределению',
    href: '/dashboard/tasks',
    component: 'TasksView',
    meta: {
      title: 'Задачи по приёму/распределению',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER, UserRoleId.OPERATOR],
  },
  {
    name: 'Схема склада',
    href: '/dashboard/warehouse-scheme',
    component: 'WarehouseSchemeView',
    meta: {
      title: 'Схема склада',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.OPERATOR],
  },
]

export default dashboardItems
