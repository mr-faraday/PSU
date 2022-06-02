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
    name: 'Оформление заявки на принятие ТМЦ',
    href: '/dashboard/receive-cargo',
    component: 'ReceiveCargoView',
    meta: {
      title: 'Оформление заявки на принятие ТМЦ',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER],
  },
  {
    name: 'Оформление заявки на возврат ТМЦ',
    href: '/dashboard/move-cargo',
    component: 'MoveCargoView',
    meta: {
      title: 'Оформление заявки на возврат ТМЦ',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER],
  },
  {
    name: 'Список задач',
    href: '/dashboard/tasks',
    component: 'TasksListView',
    meta: {
      title: 'Задачи по приёму/распределению ТМЦ',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER, UserRoleId.OPERATOR],
  },
  {
    name: 'Схема склада',
    href: '/dashboard/warehouse-scheme',
    component: 'WarehouseSchemeView',
    roles: [UserRoleId.ADMIN, UserRoleId.OPERATOR],
  },
  {
    name: 'Список ТМЦ',
    href: '/dashboard/cargos',
    component: 'CargosListView',
    meta: {
      title: 'Список ТМЦ',
    },
    roles: [UserRoleId.ADMIN, UserRoleId.MANAGER, UserRoleId.OPERATOR],
  },
]

export default dashboardItems
